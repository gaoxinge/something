package gxg.mapper;

import gxg.pojo.Db;
import org.apache.ibatis.annotations.Select;

public interface DbMapper {
    @Select("select host, db, user from db limit 1")
    Db select();
}
