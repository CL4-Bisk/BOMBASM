#include <emscripten.h>
#include <emscripten/html5.h>
#include <cmath>
#include <wasm_simd128.h>

extern "C" {
  void fast_add(float* a, float* b, float* c) {
    v128_t va = wasm_v128_load(a);
    v128_t vb = wasm_v128_load(b);
    v128_t vc = wasm_f32x4_add(va, vb);
    wasm_v128_store(c, vc);
  }
}


float x = 100, y = 100, vx = 2.0, vy = 2.0;

EM_BOOL frame(double time, void* userData) {
    x += vx;
    y += vy;
    if (x < 0 || x > 500) vx = -vx;
    if (y < 0 || y > 300) vy = -vy;

    EM_ASM({
        const ctx = Module.ctx;
        ctx.clearRect(0, 0, 500, 300);
        ctx.fillStyle = 'red';
        ctx.beginPath();
        ctx.arc($0, $1, 10, 0, 2*Math.PI);
        ctx.fill();
    }, x, y);

    return EM_TRUE;
}

int main() {
    EM_ASM({
        const canvas = document.createElement('canvas');
        canvas.width = 500;
        canvas.height = 300;
        document.body.appendChild(canvas);
        Module.ctx = canvas.getContext('2d');
    });

    emscripten_request_animation_frame_loop(frame, 0);
    return 0;
}
