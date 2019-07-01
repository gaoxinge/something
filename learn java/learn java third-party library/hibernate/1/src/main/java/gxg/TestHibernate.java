package gxg;

import gxg.utils.MysqlUtil;
import gxg.pojo.DbInfo;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import lombok.extern.slf4j.Slf4j;
import java.util.List;

@Slf4j
public class TestHibernate {
    public static void main(String[] args) {
        MysqlUtil.initDefaultSessionFactory();
        SessionFactory sessionFactory = MysqlUtil.getSessionFactory();
        Session session = sessionFactory.openSession();
        List<DbInfo> dbInfos = session.createQuery("from DbInfo").list(); // must use pojo name
        for (DbInfo dbInfo: dbInfos)
            System.out.println(dbInfo);
        session.close();
        sessionFactory.close();
    }
}
