package main

import "github.com/gin-gonic/gin"

func f(c *gin.Context) {
	c.JSON(200, gin.H{"message": "pong"})
}

func main() {
	r := gin.Default()
	r.GET("/ping", f)
	r.Run()
}