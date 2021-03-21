import java.net.*;
import java.io.*;

public class UDPSender {
	public static void main(String[] args) {
		DatagramSocket ds = null;
		DatagramPacket sendDatagramPacket = null;
		DatagramPacket receiveDatagramPacket = null;
		
		try{
			ds = new DatagramSocket(4000);
			// 포트 4000번에 소켓을 생성하였다.
			System.out.println("UDPSender 데이터그램소켓 생성");
			
			String sendMessage = "여기는 Sender~";
			// 클라이언트가 서버에게 메세지를 보낸다.
			
			byte[] sendByte = sendMessage.getBytes();
			// DatagramSocket을 통해 보내는 데이터는 byte배열이다.
			
			InetAddress destinationIA = InetAddress.getByName("127.0.0.1");
			// DatagramSocket은 전용도로가 없기 때문에 보낼때마다 수진지의 IP를 지정해 준다.
			
			sendDatagramPacket = new DatagramPacket(sendByte, sendByte.length, destinationIA, 5000);
			// 송신하는데 사용할 DatagramSocket 클래스의 인스턴스를 생성한다. (byte배열의 주소값, 배열의 길이, 수신지의 IP, 수신지의 Port)
			
			ds.send(sendDatagramPacket);
			// 윗줄에서 만들어진 '송신용 DatagramSocket 클래스의 인스턴스' 를 보낸다.
			System.out.println("메시지 전송 완료");
			
			byte[] receiveByte = new byte[512];
			// DatagramSocket을 통해 읽어오는 데이터는 byte배열이다. 
			
			receiveDatagramPacket = new DatagramPacket(receiveByte, receiveByte.length);
			// 수신하는데 사용할 DatagramSocket 클래스의 인스턴스를 생성한다.(byte배열의 주소값, 배열의 길이)
			
			ds.receive(receiveDatagramPacket);			
			// DatagramSocket 클래스의 receive 메소드이다. 데이터가 들어오면 받아들여 매개인자에 저장한다.
			
			String receiveMessage = new String(receiveDatagramPacket.getData(), 0, receiveDatagramPacket.getLength());
			// 윗줄에서 저장된 데이터를 콘솔로 출력하기 위해 byte배열을 String 클래스의 인스턴스로 변형한다. (byte배열값을 리턴, byte배열에서 데이터를 가져올 위치, 가져올 길이)
			
			System.out.println("수신 메세지: " + receiveMessage);			
		}catch(SocketException se){
			
		}catch(UnknownHostException uhe){
			
		}catch(IOException ioe){
			
		}finally{
			if(ds != null)
				ds.close();
		}
	}
}