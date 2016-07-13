## Get connection
Request
```json
{
  "type": "request",
  "message": "get",
  "resource": "/connection"
}
```
Message accepted response
```json
{
  "type": "response",
  "message": "get",
  "resource": "/connection",
  "response": {
    "code": 202
  }
}
```
Message processed notification
```json
{
  "type": "notification",
  "message": "get",
  "resource": "/connection",
  "notification": {
    "code": 200,
    "content" : {
      "type": "connection",
      "network": "network name",
      "isConnected": true
    }
  }
}
```
