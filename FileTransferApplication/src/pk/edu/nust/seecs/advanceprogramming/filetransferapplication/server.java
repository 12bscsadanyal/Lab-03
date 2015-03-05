package pk.edu.nust.seecs.advanceprogramming.filetransferapplication;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class server {
  @SuppressWarnings("resource")
public static void main(String[] args) throws IOException {
	  
	  String datafile = "D:\\Array.txt";
	  
	    MessageDigest md = null;
		try {
			md = MessageDigest.getInstance("SHA1");
		} catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	    FileInputStream fis = new FileInputStream(datafile);
	    byte[] dataBytes = new byte[1024];
	 
	    int nread = 0; 
	 
	    while ((nread = fis.read(dataBytes)) != -1) {
	      md.update(dataBytes, 0, nread);
	    };
	 
	    byte[] mdbytes = md.digest();
	 
	    //convert the byte to hex format
	    StringBuffer sb = new StringBuffer("");
	    for (int i = 0; i < mdbytes.length; i++) {
	    	sb.append(Integer.toString((mdbytes[i] & 0xff) + 0x100, 16).substring(1));
	    }
	 
	    System.out.println("Digest(in hex format):: " + sb.toString());
	  
    ServerSocket serversock = new ServerSocket(6696);
    System.out.println("Server starting");
    File myFile = new File("D:\\Array.txt");
    System.out.println(myFile.toString());
    
    while (true) {
    	
      Socket sock = serversock.accept();
      byte[] bytearray = new byte[(int) myFile.length()];
      BufferedInputStream buf = new BufferedInputStream(new FileInputStream(myFile));
      buf.read(bytearray, 0, bytearray.length);
      
      OutputStream output = sock.getOutputStream();
      System.out.println(bytearray);
      output.write(bytearray, 0, bytearray.length);
      output.flush();
      sock.close();
      System.out.println("Server Closing ");
    }
  }
}
