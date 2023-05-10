# currently mlx ver :
	(beta)mms_202020219
https://velog.io/@seomoon/M1-%EB%A7%A5%EC%97%90%EC%84%9C-minilibX-%EC%8B%A4%ED%96%89%ED%95%98%EA%B8%B0-42-cub3dminiRT
mlx mms 버전 (beta 버전)
mlx beta 버전에서는 get_screen_size() 함수를 사용할 수 있다. beta 버전을 사용하려면 인트라의 프로젝트 페이지에서 minilibx_mms_20200219_beta.tgz 파일을 다운받아서
마찬가지로 압축을 풀고 프로젝트 루트에 위치시키면 된다.

디렉토리명은 mlx_beta로 변경하고 진행했다.

베타 버전은 arm64 아키텍처에서도 실행이 되기 때문에
arch 명령어를 사용하지 않아도 된다.

gcc *.c -I. -Lmlx_beta -lmlx -framework Metal -framework Metalkit
beta 버전은 정적 라이브러리 .a 가 아닌 동적 라이브러리 .dylib 로 구성되기 때문에
opengl 버전과 똑같이 컴파일하면 dyld: Library not loaded: libmlx.dylib 에러가 발생할 수 있다.

동적 라이브러리.dylib 는 정적 라이브러리.a와 달리
컴파일 할 때 동적라이브러리의 내용이 실행파일에 포함되지 않고
실행할 때 포함이 되기 때문에 발생하는 에러이다.

해결방법은 두 가지가 있다.
Makefile에서 install_name_tool 명령어로
libmlx.dylib의 path를 설정해준다.
아니면 그냥 프로젝트 루트 디렉토리에 libmlx.dylib 파일을 두고 컴파일하면 된다.



