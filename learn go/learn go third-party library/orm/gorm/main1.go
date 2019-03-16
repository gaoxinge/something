package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"fmt"
)

const (
	host = ""
	port = 0
	user = ""
	password = ""
	dbname = ""
)

type DB struct {
	Host string `gorm:"column:Host"`
	Db   string `gorm:"column:Db"`
	User string `gorm:"column:User"`
}

func (d DB) TableName() string {
	return "db"
}

func main() {
	psqInfo := fmt.Sprintf("%s:%s@tcp(%s:%d)/%s?charset=utf8", user, password, host, port, dbname)

	db, err := gorm.Open("mysql", psqInfo)
	if err != nil {
		panic(err)
	}

	var d DB
	db.Take(&d)
	fmt.Println(d.Host, d.Db, d.User)
}