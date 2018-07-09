# wsgi vs servlet

- web container --- wsgi server
- servlet       --- wsgi app
- jsp           --- template
- struts        --- django, flask

## servlet

### basic

- web container initialize only one instance for each servlet
- web container listen to one request
- web container start a thread to run the instance of servlet

### threadlocal

```java
public class CurrentServlet extends HttpServlet {
    PrintWriter out;  // unsafe: use threadlocal
 
    public void doGet(HttpServletRequest request, 
                      HttpServletResponse response)
                      throws ServletException, IOException {
        // safe
    }
 
    public void doPost(HttpServletRequest request, 
                       HttpServletResponse response)
                       throws ServletException, IOException {
        // safe
    }
}
```