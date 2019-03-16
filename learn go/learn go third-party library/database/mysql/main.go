package main

import (
	"fmt"
	"database/sql"
	_ "github.com/go-sql-driver/mysql"
)

const (
	host = ""
	port = 0
	user = ""
	password = ""
	dbname = ""
)

func main() {
	psqInfo := fmt.Sprintf("%s:%s@tcp(%s:%d)/%s?charset=utf8", user, password, host, port, dbname)

	db, err := sql.Open("mysql", psqInfo)
	checkErr(err)

	rows, err := db.Query("SELECT host, db, user FROM db")
	checkErr(err)

	for rows.Next() {
		var h string
		var d string
		var u string

		err = rows.Scan(&h, &d, &u)
		checkErr(err)
		fmt.Println(h, d, u)
	}

	db.Close()
}

func checkErr(err error) {
	if err != nil {
		panic(err)
	}
}