## Create connection
Request
```json
{
  "type": "request",
  "message": "create",
  "resource": "/connection",
  "request": {
    "content" : {
      "type": "connection",
      "ssid": "blah",
      "password": "blah"
    }
  }
}
```
Message accepted response
```json
{
  "type": "response",
  "message": "create",
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
  "message": "create",
  "resource": "/connection",
  "notification": {
    "code": 302,
    "metadata" : {
      "location": "/connection"
    }
  }
}
```
