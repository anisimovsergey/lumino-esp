## Create connection
Request
```json
{
  "type": "request",
  "message": "create",
  "resource": "/connection",
  "content" : {
    "type": "connection",
    "ssid": "network SSID",
    "password": "password"
  }
}
```
Message accepted response
```json
{
  "type": "response",
  "message": "create",
  "resource": "/connection",
  "result": {
    "type": "statusResult",
    "code": 202
  }
}
```
Message processed notification
```json
{
  "type": "notification",
  "message": "create",
  "resource": "/connection",
  "result": {
    "type": "statusResult",
    "code": 302,
    "attributes" : {
      "location": "/connection"
    }
  }
}
```
