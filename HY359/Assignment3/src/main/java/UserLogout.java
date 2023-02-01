import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.IOException;

@WebServlet(name = "UserLogout", value = "/UserLogout")
public class UserLogout extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session=request.getSession();
        if(session.getAttribute("logged_in")!=null){
            session.invalidate();
            response.setStatus(200);
        }
        else{
            response.setStatus(403);
        }

    }
}
