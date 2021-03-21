import java.net.*;
import java.io.*;

public class Server {
	public static void main(String[] args) {
		System.out.println("Server-TCPDemo3");
		ServerSocket server = null;
		Socket client = null;
		DataInputStream dis = null;
		BufferedReader br = null;
		DataOutputStream dos = null;
		
		try{
			server = new ServerSocket(5000);
			// TCP 기반에서 서버는 ServerSocket을 생성해야 한다. 5000번 포트에 ServerSocket을 생성한다.
			System.out.println("서버 소켓 생성");
			
			client = server.accept();
			// 대기하고 있다가 클라이언트가 접속하면  접속정보를 ServerSocket 클래스에 인스턴스화 한다.
			System.out.println("클라이언트 접속");
			
			while(true){
				dis = new DataInputStream(client.getInputStream());
				// 클라이언트가 보내온 데이터를 읽기 위해 InputStream을 확보한다.
				
				String receiveMessage = dis.readUTF();
				// readUTF를 통해 전송되어온 문자열을 읽어 String 클래스의 인스턴스를 생성한다.
				System.out.println("Client : " + receiveMessage);
				// 받은 문자열을 출력한다.
				
				if(receiveMessage.equals("exit"))
					break;
					
				String sendMessage = receiveMessage.toUpperCase();
				// 받은 문자열을 대문자로 바꾼 후, 다른 String 변수에 대입한다.
			
				dos = new DataOutputStream(client.getOutputStream());
				// 윗줄에서 String에 저장된 내용을 보내기 위해선 DataOutputStream 객체를 생성해야 한다.
				
				dos.writeUTF(sendMessage);
				// writeUTF를 통해 메세지를 보낸다.
				
				if(sendMessage.equals("exit"))
					break;
			}
		}catch(IOException ioe){
			ioe.printStackTrace();
		}finally{
			try{
				if(dis != null)
					dis.close();
				if(br != null)
					br.close();
				if(dos != null)
					dos.close();
				if(client != null)
					client.close();
				if(server != null)
					server.close();
			}
			catch(IOException ioe){
				ioe.printStackTrace();
			}
		}
	}
}