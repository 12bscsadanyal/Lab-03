package pk.edu.nust.seecs.advanceprogramming.filetransferapplication;

import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.Socket;
import java.security.MessageDigest;

public class client {
  @SuppressWarnings("resource")
public static void main(String[] argv) throws Exception {
    Socket sock = new Socket("127.0.0.1", 6666);
    byte[] mybytearray = new byte[1024];
    InputStream is = sock.getInputStream();
    System.out.println("reading file");
    FileOutputStream fos = new FileOutputStream("D:\\danyal.txt");
    BufferedOutputStream bos = new BufferedOutputStream(fos);
    int bytesRead = is.read(mybytearray, 0, mybytearray.length);
    bos.write(mybytearray, 0, bytesRead);
    bos.close();
    sock.close();
    
    
    String datafile = "D:\\danyal.txt";
    
    MessageDigest md = MessageDigest.getInstance("SHA1");
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
    
    
  }
}
