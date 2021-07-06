## Lighting with a Torus Model
* 개발 환경 :C++, OpenGL, GLU, GLFW / Visual Studio 2017
* 실행 결과<br>
<kbd><img src = "https://user-images.githubusercontent.com/48857568/124611125-1ac82e80-deac-11eb-80af-143acb8c8bdf.JPG" width="800" height="500"></kbd>
* Problem Description
  * 과제 1의 torus 모델에 light를 추가시킨다.
  1. Draw a torus with the face normal vectors: toggle with the key `f`
      * Torus를 사용되는 `Face들의 Normal vector`를 그린다.
  2. Draw a torus with the vertex normal vectors: toggle with the key `v`
     * Torus를 그리는데 사용되는 `Vertex들의 Normal vector`를 그린다.
  3. Make point light, rotate and draw geometries as in the practice: key `p`
     * `Point light`를 만들고 보이도록 한다. 회전도 시킬 수 있어야 한다.
  4. Make directional light, rotate and draw geometries as in the practice: key `d`
     * `Distance light`를 만들고 보이도록 한다. 회전도 시킬 수 있어야 한다.
  5. Make spot light, rotate and draw geometries as in the practice: key `s`
     * `Spot light`를 만들고 보이도록 한다. 회전도 시킬 수 있어야 한다.
  6. Sweep angle control around the y-axis to demonstrate two-sided lighting
     * 오른쪽/왼쪽 방향키를 눌러 y축을 기준으로 Sweeping한다. light를 이용한 `two sided lighting`을 구현한다.
  7. Overlay black wireframe
