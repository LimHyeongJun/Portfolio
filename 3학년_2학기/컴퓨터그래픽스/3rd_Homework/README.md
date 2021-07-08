
## Ray Tracing of Spheres
* 개발 환경 : C++, OpenGL, GLU, GLFW / Visual Studio 2017
* 실행 결과
<kbd><img src = "https://user-images.githubusercontent.com/48857568/124925723-b508ad80-e037-11eb-9fca-da8f00282875.JPG" width="1000" height="700"></kbd>
* Problem Description
  1. Ray tracing of reflective(but not translucent) spheres `with a ray tracing depth 4`
     * 굴절만 시키는데 Ray tracing depth를 4로 한다.
  2. Ray tracing of translucent(but not reflective) spheres `without refraction`, `with a ray tracing depth 4`
     * Ray가 Sphere를 투과만 하고 반사는 일어나지 않는다.
     * Refraction이 없으므로 Ray가 굴절되지 않고 가는 방향 그대로 계속 나아간다.
  3. Ray tracing of translucent(but not reflective) spheres, `with a ray tracing depth 4`, `with a relative refractive index ηi / ηr = 2/3`
     * 굴절을 할 때는 Snell의 법칙을 쓰는데 거기에 필요한 ηi  / ηr를 2/3으로 준다.
  4. Ray tracing of reflective and reflective spheres `without reflections inside spheres`, `with a ray tracing depth 4`, `with a relative refractive index ηi  / ηr  = 2/3`
     * 구 바깥 Ray의 굴절과 반사를 모두 고려한다.
     * 다만 구 내부에서의 반사는 고려하지 않는다.
  5. Ray tracing of reflective and refractive spheres `with reflections inside spheres`, `with a ray tracing depth 4`, `with a relative refractive index ηi  / ηr  = 2/3`
     * 구 바깥 ray의 굴절과 반사를 모두 고려한다.
     * 구 내부에서의 Ray의 반사도 고려한다.
