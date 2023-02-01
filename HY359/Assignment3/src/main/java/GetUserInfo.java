import Database_HY359.src.database.tables.EditSimpleUserTable;
import Database_HY359.src.mainClasses.SimpleUser;
import org.json.JSONObject;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

@WebServlet(name = "GetUserInfo", value = "/GetUserInfo")
public class GetUserInfo extends HttpServlet {

    private void returnfailedlogin(HttpServletResponse response) {
        JSONObject jsonreply = new JSONObject();
        jsonreply.put("loged_in", false);
        jsonreply.put("message", "Username or Password is incorrect!");
        createResponse(response,403, jsonreply.toString());

    }

    private void createResponse(HttpServletResponse response, int statuscode, String data) {
        response.setStatus(statuscode);

        PrintWriter respwr = null;
        try {
            respwr = response.getWriter();
        } catch (IOException e) {
            e.printStackTrace();
        }
        respwr.write(data);
        response.setContentType("application/text");
        response.setCharacterEncoding("UTF-8");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        if(session.getAttribute("logged_in")==null){
            returnfailedlogin(response);
            return;
        }
        String logedin_id = session.getAttribute("logged_in").toString();
        String password = (String) session.getAttribute("password");


        EditSimpleUserTable usrtable = new EditSimpleUserTable();
        SimpleUser loggedin = null;
        try {
            loggedin = usrtable.databaseToSimpleUser(logedin_id, password);
        } catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }

        createResponse(response, 200, usrtable.simpleUserToJSON(loggedin).toString());
    }
}
