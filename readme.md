cub3D
=====

## 요청 함수 정리.
1. get_relative_color 함수
    
    int  get_relative_color(t_data *data, double target_height, double pixel_height, int direction)
    
내가 그리고자 하는 벽의 총 길이와, 내가 찍고자 하는 픽셀의 높이와 방위값을 넣어주면 data 에서 뽑아오는 이미지의 총 길이와 비례식을 세워서
해당 벽의 색을 반환하는 함수.

### 인자 정리.
> data : image[4] 를 담고있는 구조체.
> target_height : 이미지를 mapping 하고자 하는 실제 벽의 총 길이.
> pixel_height: 벽의 바닥을 0, 꼭대기를 target_height 라고 할 때, 내가 찍고자 하는 pixel 의 높이.
> direction : 동 서 남 북 중 어떤 방향의 벽이 필요한 지 판별을 위한 인자. 각 숫자는 매크로로 정의되어있으니 참고.

## 필요한 점.
1. 플레이어와 벽 사이의 거리에 따라서 화면에 얼마나 벽이 높게 찍여야 하는지 비례식이 필요한데 이거 좀 구해주시고
2. 이미지에서 좌표 값을 넣으면 해당 부분 색을 반환하는 식이 반드시 있을 텐데 이거 utils.c 파일 안에 작성했습니다. 근데 이거 맞는지 확인 한번 해주셈ㅋㅋ
3. 2번에서도 비례식이 있을텐데, 이 비례식도 찾아주시면 ㄱㅅ <-y값
