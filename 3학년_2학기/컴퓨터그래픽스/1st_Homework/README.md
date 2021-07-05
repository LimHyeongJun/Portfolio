
## Building/Drawing a Polygonal Torus Mode
* 개발 환경 : C++, OpenGL, GLU, GLFW / Visual Studio 2017
* 실행 결과<br>
<kbd><img src = "https://user-images.githubusercontent.com/48857568/124469446-580dbd00-ddd5-11eb-9525-222c2eb278a6.JPG" width="800" height="400"></kbd>
* Problem Description
  * 18개의 circle curve points를 계산한다.
  * y축을 중심으로 한 방향으로 36번 회전시켜 최종적으로 torus의 모양이 나오게 한다.
  * torus를 이루는 point들은 `vec3 p[36][18]`에 저장한다.
  1. Draw the wireframe only
     * torus의 wireframe만 그리는 결과.
  2. Draw the quads and the wireframe
     * `GL_QUADS`를 이용해서 torus를 quads로 그리고 wireframe을 overlay 시킴.
  3. Sweep angle control around the y-axis
     * y축을 기준으로 원을 회전시킴.
     * 오른쪽 화살표를 누르는 경우 y축으로 10도 증가시킴.
     * 왼쪽 화살표를 누르는 경우 y축으로 10도 감소시킴.
  4. Two-sided constant shading
     * torus의 안쪽 면과 바깥쪽 면의 색깔을 다르게 줌.
     * 바깥 면은 파란색, 안쪽 면은 빨간색을 줌.
