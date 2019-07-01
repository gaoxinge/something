package gxg;

import gxg.utils.MysqlUtil;
import gxg.pojo.Db;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class TestMybatis {
    public static void main(String[] args) throws Exception {
        SqlSessionFactory sessionFactory = MysqlUtil.getSessionFactory("mysql");
        SqlSession session = sessionFactory.openSession();
        Db db = session.selectOne("gxg.mapper.DbMapper.select");
        System.out.println(db);
        session.close();
    }
}
