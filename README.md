# Robotbattle
CAD STL 파일은 CAD Branch에 올라갑니다.

* nrf_read 코드에서 모터 연결선은 1,2,3,4번 핀으로 설정되어 있습니다.
* nrf_read 코드 내부에 5,6번 핀은 모터 속도 조절용으로 설정되어 있습니다.
 * 전진(foward) 후진(backward) 함수 내 주석으로 써져 있음.
* send 코드는 바꿀 게 없으나 더 강한 출력을 원한다면 RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX 등으로 설정할 수 있습니다.
