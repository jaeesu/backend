import java.net.*;
import java.io.*;

public class Client {
	public static void main(String[] args) {
		System.out.println("Client-TCPDemo3");
		Socket client = null;
		DataOutputStream dos = null;
		BufferedReader br = null;
		DataInputStream dis = null;
		
		try{
			client = new Socket("localhost", 5000);
			// 5000번 포트에 소켓 생성
			System.out.println("서버 접속 성공");
			
			while(true){
				System.out.print("Client : ");
				br = new BufferedReader(new InputStreamReader(System.in));
				// 키보드로 문자열을 입력 받아 서버로 보내기 위해 BufferedReader 클래스의 인스턴스를 생성한다.
				
				String sendMessage = br.readLine();
				// 키보드로부터 입력된 한 라인을 읽어 String 에 저장한다.
				
				dos = new DataOutputStream(client.getOutputStream());
				// 윗줄에서 String에 저장된 내용을 보내기 위해선 DataOutputStream 객체를 생성해야 한다.
				
				dos.writeUTF(sendMessage);
				// writeUTF를 통해 메세지를 보낸다.
				
				dos.flush();
				// 버퍼의 내용을 즉시 송신하라는 명령어이다.
				// 데이터를 전송하면 바로 송싱되는 것이 아니라 일단 적정량이 쌓인 이후에 보내게 되는데
				// flush() 명령어는 즉시 보낼 수 있다.
				
				if(sendMessage.equals("exit"))
					break;
				
				dis = new DataInputStream(client.getInputStream());
				// 서버가 보내온 데이터를 읽기 위해 InputStream을 확보한다. 
				
				String receiveMessage =  dis.readUTF();
				// readUTF를 통해 전송되어온 문자열을 읽어 String 클래스의 인스턴스를 생성한다.
				System.out.println("Server : " + receiveMessage);
				
				if(receiveMessage.equals("exit"))
					break;
			}
		}catch(IOException ioe){
			ioe.printStackTrace();
		}finally{
			try{
				if(br != null)
					br.close();
				if(dos != null)
					dos.close();
				if(client != null)
					client.close();
			}catch(IOException ioe){
				ioe.printStackTrace();
			}
		}
	}
}