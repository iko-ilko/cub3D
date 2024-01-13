cub3D
=====

## 1. 요청 함수 정리.

### 1. get_relative_color 함수

```C
int  get_relative_color(t_image *image[4], double total, double current, int direction)
```

* 개요
  * 내가 그리고자 하는 벽 좌표의 이미지 픽샐 색깔을 반환하는 함수.

* 1-1. 인자 정리.

  * image : image[4] 의 주소. 이미지 포인터와 이미지 heigh 가 필요.
  * total : 실제 벽의 높이.
  * current : 벽의 바닥의 높이값을 0, 꼭대기를 total - 1 이라고 할  때, 현재 픽셀의 높이.
  * direction : 동 서 남 북 중 어떤 방향의 벽이 필요한 지 판별을 위한 인자. 각 숫자는 매크로로 정의되어있다.

## 공부하는 방향 제시

1. 500x500 화면에서 중앙에 100x100 사이즈의 사각형을 그린다.
2. key_hook 을 통해서 방향키를 누르면 이 사각형이 이동할 수 있도록 한다.
3. 윈도우의 테두리를 만나면 이동을 멈추게 브레이크 조건문을 넣어준다.