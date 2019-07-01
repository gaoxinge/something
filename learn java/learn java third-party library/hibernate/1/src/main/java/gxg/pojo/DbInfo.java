package gxg.pojo;

import lombok.Data;
import lombok.ToString;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Column;
import java.io.Serializable;

@ToString
@Data
@Entity
@Table(name="db")
public class DbInfo implements Serializable { // pojo with composite key must implements Serializable
    @Id
    @Column(name="host")
    private String hostName;

    @Id
    @Column(name="db")
    private String dbName;

    @Id
    @Column(name="user")
    private String userName;
}
