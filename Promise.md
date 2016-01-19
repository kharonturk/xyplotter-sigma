x -> p -> y -> StartXYPlotter -> TakePictureFindPoint -> r -> d -> SendDataPacket


# x : AVR이 시작되었다는 것을 알림.

# p : MATLAB이 시작되었다는 것을 알림.

# y : START\_INT : AVR에서 PictureEdge를 찾아라고 명령.

# r : MATLAB에서 data를 보낼 준비가 되었다고 알림.

# d : SEND\_INT : AVR에서 data를 요구함.


PORTC : L298N 드라이버
PORTA : 다른 드라이버

Red -> Blue -> Yellow -> Orange

PORT0 -> 2 -> 4 -> 6

Black, White : common