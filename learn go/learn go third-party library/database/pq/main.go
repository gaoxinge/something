package main

import (
	"fmt"
	"database/sql"
	_ "github.com/lib/pq"
)

const (
	host = ""
	port = 0
	user = ""
	password = ""
	dbname = ""
)

func main() {
	psqInfo := fmt.Sprintf("host = %s port = %d user = %s password = %s dbname = %s sslmode = disable", host, port, user, password, dbname)

	db, err := sql.Open("postgres", psqInfo)
	checkErr(err)

	rows, err := db.Query("SELECT id, crowdname, crowdvalue FROM zs_crowd_hash LIMIT 1")
	checkErr(err)

	for rows.Next() {
		var id int
		var crowdname string
		var crowdvalue int

		err = rows.Scan(&id, &crowdname, &crowdvalue)
		checkErr(err)
		fmt.Println(id, crowdname, crowdvalue)
	}

	db.Close()
}

func checkErr(err error) {
	if err != nil {
		panic(err)
	}
}