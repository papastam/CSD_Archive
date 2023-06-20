package hy452.ws.rest;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.QueryParam;

@Path("CitySearch") //set your service url path to <base_url>/hello
// the <base_url> is based on your application name, the servlet 
// and the URL pattern from the web.xml configuration file
public class CitySearch{
	// This method is called if TEXT_PLAIN is requested
	@GET
	@Produces(MediaType.TEXT_PLAIN) //defines which MIME type is delivered by a method annotated with @GET
	public String convertInch(@QueryParam("city") String city) throws IOException { 

		if(city==null){return null;}
		
		URL url = new URL("https://api.openweathermap.org/data/2.5/weather?q="+city+"&mode=xml&appid=2144527af17f383e91ad2a7efcd8c87b");
		HttpURLConnection con = (HttpURLConnection) url.openConnection();
		con.setRequestMethod("GET");
		
		BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
		String inputLine;
		StringBuffer content = new StringBuffer();
		while ((inputLine = in.readLine()) != null) {
		    content.append(inputLine);
		}
		in.close();
		
		return content.toString();
	}
}