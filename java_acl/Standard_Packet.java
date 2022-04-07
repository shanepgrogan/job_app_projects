import java.util.*;

public class Standard_Packet{

    private String src;

    Standard_Packet(String src){
        this.src = src;
    }

    public String getSource(){
        return this.src;
    }

    public void printPacket(){
        System.out.println(this.src);
    }

}