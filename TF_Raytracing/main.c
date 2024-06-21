
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 1024
#define HEIGHT 768
#define FOV 1.05f // 60 graus

// gcc main.c -o main -lm && ./main

typedef struct vector3f {
    float x, y, z;
}Vector3f;

typedef struct material{
    float refr_i;
    float spec_exp;
    float albedo[4];
    Vector3f diff_color;
} Material;

typedef struct sphere{
    Vector3f center;
    float rad;
    Material mat;
} Sphere;

typedef struct triangle{
    Vector3f v1, v2, v3;
    Material mat;
} Triangle;

typedef struct sphere_intersect{
    int v;
    float r;
} SphereIntersect;

typedef struct trian_intersect{
    int v;
    float r;
} TriangleIntersect;

typedef struct scene_intersect{
    int v;
    Vector3f v1, v2;
    Material mat;
} SceneIntersect;

Vector3f vec3f_add(Vector3f v1, Vector3f v2){
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}

Vector3f vec3f_subtract(Vector3f v1, Vector3f v2){
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

float vec3f_sumMultiply(Vector3f v1, Vector3f v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vector3f vec3f_multiplyVal(Vector3f v1, float v){
    v1.x *= v;
    v1.y *= v;
    v1.z *= v;
    return v1;
}

Vector3f vec3f_invert(Vector3f v1){
    v1.x = -v1.x;
    v1.y = -v1.y;
    v1.z = -v1.z;
    return v1;
}

Vector3f vec3f_cross(Vector3f v1, Vector3f v2){
    Vector3f r;
    r.x = v1.y * v2.z - v1.z * v2.y;
    r.y = v1.z * v2.x - v1.x * v2.z;
    r.z = v1.x * v2.y - v1.y * v2.x;
    return r;
}

void vec3f_print(Vector3f v){
    printf("%f %f %f\n", v.x, v.y, v.z);
}

float norm(Vector3f v1){
    return sqrtf((v1.x*v1.x) + (v1.y*v1.y) + (v1.z*v1.z));
}

Vector3f normalized(Vector3f v1){
    float vn = norm(v1);
    if (vn != 0.0f){
        float inv_n = 1.0f / vn;
        return vec3f_multiplyVal(v1, inv_n);
    }
    return v1;
}

Vector3f triangle_normal(Triangle t){
    Vector3f e1 = vec3f_subtract(t.v2, t.v1);
    Vector3f e2 = vec3f_subtract(t.v3, t.v1);
    return vec3f_cross(e1, e2);
}

#define M_IVORY {1.0f, 50.0f, {0.9f, 0.5f, 0.1f, 0.0f}, {0.4f, 0.4f, 0.3f}}
#define M_GLASS {1.5f, 125.0f, {0.0f, 0.9f, 0.1f, 0.8f}, {0.6f, 0.7f, 0.8f}}
#define M_REDRUBBER {1.0f, 10.0f, {1.4f, 3.0f, 0.0f, 0.0f}, {0.3f, 0.1f, 0.1f}}
#define M_MIRROR {1.0f, 1425.0f, {0.0f, 16.0f, 0.8f, 0.0f}, {1.0f, 1.0f, 1.0f}}
#define M_TESTE {1.0f, 10.0f, {0.9f, 1.0f, 0.1f, 0.0f}, {0.0f, 0.1f, 0.0f}}

const int n_spheres = 5;
const Sphere spheres[] = {
    {{-5.0f, 0.0f, -16.0f}, 2, M_IVORY},
    {{-1.0f, -1.5f, -12.0f}, 2, M_GLASS},
    {{1.5f, -0.5f, -18.0f}, 3, M_REDRUBBER},
    {{7.0f, 5.0f, -18.0f}, 4, M_MIRROR},
    {{0.0f, -25.0f, -12.0f}, 20, M_TESTE}
};

const int n_triangles = 2;
const Triangle triangles[] = {
    {{0.0f, 2.0f, -24.0f}, {0.0f, 8.0f, -16.0f}, {-5.0f, 2.0f, -24.0f}, M_MIRROR},
    {{-5.0f, 2.0f, -24.0f}, {-5.0f, 8.0f, -16.0f}, {-0.0f, 8.0f, -16.0f}, M_MIRROR},
};

const int n_lights = 3;
const Vector3f lights[] = {
    {-20.0f, 20.0f, 20.0f},
    {30.0f, 50.0f, -25.0f},
    {30.0f, 20.0f, 30.0f}
};

Vector3f reflect(Vector3f v1, Vector3f v2){
    float d_prod = 2.0f * vec3f_sumMultiply(v1, v2);
    v2 = vec3f_multiplyVal(v2, d_prod);
    return vec3f_subtract(v1, v2);
}

Vector3f refract(Vector3f v1, Vector3f v2, float eta1, float eta2){
    float cosi = - fmaxf(-1.0f, fminf(1.0f, vec3f_sumMultiply(v1, v2)));
    if (cosi < 0.0f)
        return refract(v1, vec3f_invert(v2), eta2, eta1);
    float eta = eta2 / eta1;
    float k = 1.0f - eta*eta*(1.0f - cosi*cosi);
    if (k < 0.0f)
        return (Vector3f){1.0f, 0.0f, 0.0f};
    return vec3f_add(vec3f_multiplyVal(v1, eta), vec3f_multiplyVal(v2, eta*cosi-sqrtf(k)));
}

SphereIntersect raySphereIntersection(Vector3f v1, Vector3f v2, Sphere s){
    Vector3f l = vec3f_subtract(s.center, v1);
    float tca = vec3f_sumMultiply(l, v2);
    float d2 = vec3f_sumMultiply(l, l) - tca*tca;

    if (d2 > s.rad*s.rad)
        return (SphereIntersect){0, 0.0f};
    
    float thc = sqrtf(s.rad*s.rad - d2);
    float t0 = tca - thc;
    float t1 = tca + thc;
    if (t0 > 0.001f)
        return (SphereIntersect){1, t0};
    if (t1 > 0.001f)
        return (SphereIntersect){1, t1};
    return (SphereIntersect){0, 0.0f};
}

TriangleIntersect rayTriangleIntersection(Vector3f v1, Vector3f v2, Triangle t){
    Vector3f e1 = vec3f_subtract(t.v2, t.v1);
    Vector3f e2 = vec3f_subtract(t.v3, t.v1);
    Vector3f cross_e2 = vec3f_cross(v2, e2);
    float det = vec3f_sumMultiply(e1, cross_e2);
    if (det > -0.001f && det < 0.001f)
        return (TriangleIntersect){0, 0.0f};

    float inv_det = 1.0f / det;
    Vector3f s = vec3f_subtract(v1, t.v1);
    float u = inv_det * vec3f_sumMultiply(s, cross_e2);
    if (u < 0.0f || u > 1.0f)
        return (TriangleIntersect){0, 0.0f};
    
    Vector3f q = vec3f_cross(s, e1);
    float v = inv_det * vec3f_sumMultiply(v2, q);
    if (v < 0.0f || u + v > 1.0f)
        return (TriangleIntersect){0, 0.0f};
    
    float d = inv_det * vec3f_sumMultiply(e2, q);
    if (d > 0.001f)
        return (TriangleIntersect){1, d};
    return (TriangleIntersect){0, 0.0f};
}

SceneIntersect raySceneIntersect(Vector3f v1, Vector3f v2){
    int h=0;
    Vector3f pt, N;
    Material material;
    float nearest_dist = 1e10f;

    for (int i=0;i<n_spheres;i++){
        Sphere s = spheres[i];
        SphereIntersect sphere_inters = raySphereIntersection(v1, v2, s);
        if (!sphere_inters.v || sphere_inters.r > nearest_dist)
            continue;
        nearest_dist = sphere_inters.r;
        pt = vec3f_add(v1, vec3f_multiplyVal(v2, nearest_dist));
        N = normalized(vec3f_subtract(pt, s.center));
        material = s.mat;
        h = 1;
    }
    for (int i=0;i<n_triangles;i++){
        Triangle t = triangles[i];
        TriangleIntersect triangle_inters = rayTriangleIntersection(v1, v2, t);
        if (!triangle_inters.v || triangle_inters.r > nearest_dist)
            continue;
        nearest_dist = triangle_inters.r;
        pt = vec3f_add(v1, vec3f_multiplyVal(v2, nearest_dist));
        N = normalized(triangle_normal(t));
        material = t.mat;
    }
    int v;
    if (nearest_dist < 1000.0f)
        v = 1;
    else 
        v = 0;
    return (SceneIntersect){v, pt, N, material};
}

Vector3f castRay(Vector3f v1, Vector3f v2, int depth){
    SceneIntersect si = raySceneIntersect(v1, v2);
    if (depth > 4 || !si.v)
        return (Vector3f){0.2f, 0.7f, 0.8f}; // Background Color
    
    Vector3f reflect_d = normalized(reflect(v2, si.v2));
    Vector3f refract_d = normalized(refract(v2, si.v2, si.mat.refr_i, 1.0f));
    Vector3f reflect_c = castRay(si.v1, reflect_d, depth+1);
    Vector3f refract_c = castRay(si.v1, refract_d, depth+1);

    float diff_light_intens = 0.0f;
    float spec_light_intens = 0.0f;
    for (int i=0;i<n_lights;i++){
        Vector3f light = lights[i];
        Vector3f light_d = normalized(vec3f_subtract(light, si.v1));
        SceneIntersect shadow = raySceneIntersect(si.v1, light_d);
        if (shadow.v && (norm(vec3f_subtract(shadow.v1, si.v1))) < (norm(vec3f_subtract(light, si.v1))))
            continue;
        diff_light_intens += fmaxf(0.0f, vec3f_sumMultiply(light_d, si.v2));
        spec_light_intens += powf(fmaxf(0.0f, vec3f_sumMultiply(vec3f_invert(reflect(vec3f_invert(light_d), si.v2)), v2)), si.mat.spec_exp);
    }

    Vector3f color;
    color = vec3f_multiplyVal(si.mat.diff_color, diff_light_intens * si.mat.albedo[0]);
    color = vec3f_add(color, vec3f_multiplyVal((Vector3f){1.0f, 1.0f, 1.0f}, spec_light_intens * si.mat.albedo[1]));
    color = vec3f_add(color, vec3f_multiplyVal(reflect_c, si.mat.albedo[2]));
    color = vec3f_add(color, vec3f_multiplyVal(refract_c, si.mat.albedo[3]));

    return color;
}

int main(){
    Vector3f* frameBuffer = (Vector3f*)malloc(WIDTH * HEIGHT * sizeof(Vector3f));
#pragma omp parallel for
    for (int pix=0;pix<WIDTH*HEIGHT;pix++){
        Vector3f d;
        d.x = (pix % WIDTH + 0.5f) - WIDTH / 2.0f;
        d.y = -(pix / WIDTH + 0.5f) + HEIGHT / 2.0f;
        d.z = -HEIGHT / (2.0f * tan(FOV / 2.0f));
        frameBuffer[pix] = castRay((Vector3f){0.0f, 0.0f, 0.0f}, normalized(d), 0);
    }

    FILE* f = fopen("./out.ppm", "wb");
    fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    for (int i=0;i<WIDTH * HEIGHT;i++){
        Vector3f c = frameBuffer[i];
        float max = fmaxf(1.0f, fmaxf(c.x, fmaxf(c.y, c.z)));
        fputc((unsigned char)(255 * c.x / max), f);
        fputc((unsigned char)(255 * c.y / max), f);
        fputc((unsigned char)(255 * c.z / max), f);
    }
    fclose(f);
    free(frameBuffer);
    return 0;
}
