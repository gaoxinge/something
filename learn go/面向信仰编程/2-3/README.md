# 反射

```    
         typecast                      TypeOf/ValueOf
       ---------->                   ----------------->
Value    typecast   Interface Value    Interface         Reflection Object
       <----------                   <-----------------
```

- 从接口值可反射出反射对象
- 从反射对象可反射出接口值
- 要修改反射对象，其值必须可设置