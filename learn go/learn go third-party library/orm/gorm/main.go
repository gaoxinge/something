package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/postgres"
	"fmt"
)

const (
	host = ""
	port = 0
	user = ""
	password = ""
	dbname = ""
)

type HashValue struct {
	Id int
	Crowdname string
	Crowdvalue int
}

func (hashValue HashValue) TableName() string {
	return "zs_crowd_hash"
}

func main() {
	psqInfo := fmt.Sprintf("host = %s port = %d user = %s password = %s dbname = %s sslmode = disable", host, port, user, password, dbname)

	db, err := gorm.Open("postgres", psqInfo)
	if err != nil {
		panic(err)
	}

	var hashValue HashValue
	db.Take(&hashValue)
	fmt.Println(hashValue.Id, hashValue.Crowdname, hashValue.Crowdvalue)
}