package hy452.ws.rest;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.QueryParam;

@Path("inch_to_cm") //set your service url path to <base_url>/hello
// the <base_url> is based on your application name, the servlet 
// and the URL pattern from the web.xml configuration file
public class cm_to_inch{
	// This method is called if TEXT_PLAIN is requested
	@GET
	@Produces(MediaType.TEXT_PLAIN) //defines which MIME type is delivered by a method annotated with @GET
	public double convertInch(@QueryParam("inch") double inch) { 
		return inch * 2.54;
	}
}