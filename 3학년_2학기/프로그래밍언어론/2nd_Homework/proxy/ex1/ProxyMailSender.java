package proxy.ex1;

public class ProxyMailSender implements MailSender{
	private RealMailSender mailSender;
	
	public ProxyMailSender() {
		mailSender = new RealMailSender();
	}
	
	public void send(String message) {
		System.out.println("Proxy before process");
		mailSender.send(message);
		System.out.println("Proxy after process");
	}
}
