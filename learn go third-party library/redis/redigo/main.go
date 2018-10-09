package main

import (
	"github.com/gomodule/redigo/redis"
	"fmt"
)

func main() {
	c, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		panic(err)
	}

	_, err = c.Do("SET", "mykey", "superWang")
	if err != nil {
		panic(err)
	}

	mykey, err := redis.String(c.Do("GET", "mykey"))
	if err != nil {
		panic(err)
	}
	fmt.Println(mykey)

	_, err = c.Do("DEL", "mykey")
	if err != nil {
		panic(err)
	}

	exist, err := redis.Bool(c.Do("EXISTS", "mykey"))
	if err != nil {
		panic(err)
	}
	fmt.Println(exist)

	c.Close()
}