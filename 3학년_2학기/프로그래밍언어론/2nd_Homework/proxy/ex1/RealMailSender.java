package proxy.ex1;

public class RealMailSender implements MailSender {
	public void send(String message) {
		System.out.println("[SEND]: " + message);
	}
}
