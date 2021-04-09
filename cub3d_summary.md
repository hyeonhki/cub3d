
- Mandatory part - cub 3d
  - external func
  : open, close, read, write, printf, malloc, free, perror, strerror, exit
  : math library
  : minilibx
  - libft ok
	- 창 변경, 최소화 등 관리가 원활
	- 벽의 동서남북이 다른 texture를 가져야한다.
	- 벽 대신 스프라이트(아이템)을 표시할 수 있어야 한다.
	- 바닥과 천장 색상을 2개로 설정할 수 있어야 한다
	- 프로그램에 두번 째 인수가 "--save"일 경우 렌더링된 이미지를 bmp 형식으로 저장해야한다.
	- 두번째 인수가 없을 경우 프로그램은 창에 이미지를 표시하고 다음 규칙 준수
    	- 키보드의 왼쪽과 오른쪽 화살표 키는 미로에서 좌우를 볼 수 있도록한다
    	- WASD 키를 사용하여 미로를 통해 시야를 이동할 수 있어야 한다
    	- ESC 창종료
    	- 창틀의 닫기 버튼 클릭시 프로그램이 깨끗이 종료될 것
    	- 지도에서 선언된 화면 크기가 디스플레이 해상도보다 크면 현재 디스플레이 해상도에 따라 윈도우 크기가 설정된다.
	- .cub인 맵 설명 파일이 첫 번째 인수가 된다
    	- 빈칸은 0, 벽면 1, 아이템 2, 플레이어의 사작위치와 산란 방향의 경우를 NSEW로
  	- 지도는 벽으로 둘러싸거나 닫혀있어야 한다. 그렇지 않으면 프로그램 오류를 반환
  	- 지도 내용 외에는 각 요소의 유형을 하나 이상의 빈 줄로 구분할 수 있다
  	- 지도를 제외한 요소별 정보 유형별 구분은 1개 이상의 공백으로 할 수 있다.
  	- 항상 지도는 마지막 콘텐츠, 다른 것들은 순서 상관 x
  	- 지도에서 공백은 유효한 부분으로 처리하기 나름
  	- 각 요소(지도 제외) 첫 번째 정보는 유형 식별자(하나 또는 두개의 문자로 구성)이며, 그 두에 각 객체에 대한 모든 특정 정보가 다음과 같이 엄힐한 순서로 표시된다.
  	- 파일에서 잘못된 구성이 발견되면 프로그램을 올바르게 종료하고 "Error\n"을 반환한 후 선택한 명시적 오류 메세지를 반환한다!

### 구현 궁금증 정리
1. 렌더링 사이즈는 화면 크기를 말하는 것인가? 해상도라면 뭘 말하는지..?
2. 지도에서 선언된 화면 크기가 디스플레이 해상도보다 크면 현재 디스플레이 해상도에 따라 윈도우 크기가 결정된다라는 말이 무엇인지
3. 
### 서브젝트 정리
- 지도
  - 사용자의 위치가 표시되어야한다.
  - 벽으로 둘러싸여 있어야 한다
  - 지도를 제외하고 지도파일에 개행이 있거나 띄워져 있을 수 있음
  - 지도는 맨 마지막, 나머지는 순서 변경 가능
  - 규칙을 준수하는 한 맵에 공백도 가능
  - 각각의 요소들은 첫 글자로 구분가능



### mlx 예제 정리
####1. 소프트웨어와 디스플레이 연결
 - ```c
	void *mlx_init()
   ```
    - 모든 것 이전에 필요한 함수.
    - 내 소프트웨어와 디스플레이를 연결해준다.
    - 연결 실패시 NULL 리턴 혹은 (void *)0 리턴
	- 전반적인 프레임워크 지식없이 그래픽 소프트웨어를 쉽게 만들 수 있음
___
####2. window
  - ```c
  	void *mlx_new_indow(void *mlx_ptr, int size_x, int size_y, char *title)
	```
    - 새 창을 스크린에 띄운다.
    - size_x, size_y = 창 사이즈
    - title = 창의 타이틀 바에 표시된다.
    - mlx_ptr = mlx_init이 반환한 연결 식별자
    - 창 생성 실패시 NULL(void *0)
    - 성공시 새로운 윈도우 식별자인 void *를 준다.
  - ```c
  	int mlx_clear_window(void *mlx_ptr, void *win_ptr)
	```
	- 매개변수로 받은 win_ptr을 검은색으로 clear
  - ```c
  	int mlx_destroy_window(void *mlx_ptr, void *win_ptr)
	``` 
	- 매개변수로 받은 win_ptr로 윈도우를 destroy
___
####3. image
- ```c
	void *mlx_new_image(void *mlx_ptr, int width, int height)
  ```
	- 새 이미지를 메모리에 생성
	- 에러 발생시 NULL 리턴
	- 나중에 이 이미지를 조작할 때 필요한 이미지 식별자인 void *를 리턴한다.
	- 이미지 사이즈와 mlx_ptr연결 식별자만 있으면 된다.
- ```c
	char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian)
	```
	- __반환값이 문자열인데 왜 배열로 형변환?__
		- 메모리크기, 바이트 등과 관련있는 듯. void * 로 캐스팅하면 밑에 참조할때 4를 곱해야한다는데 왜지?(keuhdall's github가면 더 자세한 정보)
	- 생성된 이미지에 대한 정보를 리턴해서 사용자가 나중에 이미지를 수정할 수 있도록하는 함수
	- img_ptr는 사용할 이미지
	- bits_per_pixel = 픽셀 색상 (이미지의 깊이)을 나타내는 데 필요한 비트 수
	- size_line = 이미지의 한 줄을 메모리에 저장하는 데 사용되는 바이트 수. 이 정보는 이미지에서 한 줄에서 다른 줄로 이동하는 데 필요
	- ___endian = 이미지의 픽셀 색상을 리틀 엔디안 또는 빅엔디안으로 저장해야하는 지 알려줍니다___ 
		- 리틀 엔디언(0) : 앞 주소에 작은 바이트붵 기록. 인텔계열의 디폴트
		- 빅 엔디언(1) : 앞 주소에 큰 바이트부터 기록. 사람 생각과 비슷
	- 이미지가 저장된 메모리 영역의 시작을 나타내는 char *주소를 리턴한다.
	- bits_per_pixel, size_line, endian 은 저장할 변수만 잘 넣어주면 알아서 정보를 잘 받아온다고 함.
	- height * width 만큼의 배열로 이미지를 표현하는 듯.
- ```c
	int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y)
	```
	- 디스플레이 연결(mlx_ptr), 사용할 창(win_ptr) 및 이미지(img_ptr), 창에서 이미지를 배치할 위치(x,y)
- ```c
	void *mlx_xpm_file_to_image (void *mlx_ptr, char *filename, int *width, int *height);
	```
	- 에러 발생시 null 리턴
	- mlx_A_to_image 함수들은 각각 xpm 배열데이터, xpm파일, png파일의 종류 별 이미지 변환.
	- width와 hegith에는 너비와 높이를 저장할 int 형 변수의 주소를 넣어둔다.
- ```c
	void *mlx_destroy_image(void *mlx_ptr, void *img_ptr)
	```
	- __무엇일까?__
___
####4. loop & hook
- ```c
  int mlx_loop(void *mlx_ptr)
  ```
    - 이벤트를 받기위해 필요한 함수
	- 그래픽 시스템은 두방향 (1. screen dispaly, 2. 키보드 마우스 정보 얻어오기)
    - 리턴 X, 키보드나 마우스로부터 받은 이벤트를 기다리는 무한루프, 이벤트에 연결되는 사용자정의 함수를 호출
    - mlx_ptr 이 피라미터
	- __마지막에 이걸 쳐줘야 프로그램이 종료되지 않고 계속돌아감__
<br>
-	```c
	int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param)
	```
	- funct_ptr는 이벤트 발생시 호출하고 싶은 함수를 가리키는 포인터
	- 키도 입력 등의 이벤트를 감지해서 작동
	- funct는 win_ptr에 의해 특정된 윈도우에만 적용
	- x_event에 정의해놓은 X11 이벤트(ex. KEY press = 2)를 넣음
	- __x_mask?__
	- 예시. funct에서 key_press에서 int로 입력받은 이벤트에 따라 함수 동작
<br>
- mlx_key_hook, mlx_mouse_hook, mlx_expose_hook 함수는 같은 방식으로 동작
<br>

- ```c
	int mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param)
	```
	- 아무 이벤트도 일어나지 않을 경우 인자로 받았던 함수가 호출된다.
	- 레이캐스팅의 출력값을 통해 화면 뿌리기 용으로 사용
	- 이벤트를 포착했을 경우, Minilibx는 아래와 같이 해당 함수를 고정 피라미터로 호출한다. (임의 이름)
		- expose_hook(void *param);
		- key_hook(int keycode, void *param);
		- mouse_hook(int button, int x, int y, void *param);
		- loop_hook(void *param);

### 용어 설명
1. Hooks
- 소프트웨어 요소들 사이에 전달되는 함수 호출이나 메세지 혹은 이벤트 등을 인터셉트해서 OS, APP에 행동을 변경하는 데 사용하는 말
- 키입력, 마우스 입력 등의 입력을 통해 다른 역할을 수행 시키는 것

2. events
- 이벤트는 상호작용을하는 app의 근본
- X11 이벤트 => minilibx에서 사용되는 이벤트
	- https://harm-smits.github.io/42docs/libs/minilibx/events.html

### 참고
> https://malbongcode.tistory.com/149