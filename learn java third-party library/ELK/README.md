## architecture

```
           Logstash ---> ElasticSearch ---> Kibana
Kafka ---> Logstash ---> ElasticSearch ---> Kibana
```

Kafka: message queue
Logstash: pipeline or stream to handle log
ElasticSearch: server to search log
Kibana: client to show log

## install

- [Windows环境下ELK平台的搭建](https://www.cnblogs.com/pilihaotian/p/5805525.html)
- [ELK(ElasticSearch, Logstash, Kibana)搭建实时日志分析平台](https://my.oschina.net/itblog/blog/547250)