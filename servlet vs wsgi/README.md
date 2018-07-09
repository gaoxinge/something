# servlet vs wsgi

## analogy

- web container --- wsgi server
- servlet       --- wsgi app
- jsp           --- template
- struts        --- flask

## MVC, REST

- MVC, REST: architecture
- servlet, wsgi: protocol
- servlet, wsgi have nothing to do with MVC, REST

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

## wsgi

### basic

- wsgi server listen to one request
- process: wsgi server start a process to run wsgi app 
- thread: wsgi server start a thread to run wsgi app
- wsgi app follows 

```
parse environ ---> handle reqeust ---> return response
```

### safe

- wrap wsgi app to local

### unsafe

- extract reqeust to global
- threadlocal and ctx
