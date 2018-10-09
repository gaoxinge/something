package main

import (
	_ "github.com/go-sql-driver/mysql"
	"fmt"
	"database/sql"
	"github.com/astaxie/beedb"
)

const (
	host = ""
	port = 0
	user = ""
	password = ""
	dbname = ""
)

type DB struct {
	Host string `sql:"Host" tname:"db"`
	Db   string `sql:"Db"`
	User string `sql:"User"`
}

func main() {
	psqInfo := fmt.Sprintf("%s:%s@tcp(%s:%d)/%s?charset=utf8", user, password, host, port, dbname)
	db, err := sql.Open("mysql", psqInfo)
	if err != nil {
		panic(err)
	}

	orm := beedb.New(db)

	var d DB
	orm.Where("Host = ?", "localhost").Find(&d)
	fmt.Println(d.Host, d.Db, d.User)
}