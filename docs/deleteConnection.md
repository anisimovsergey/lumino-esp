## Delete connection
Request
```json
{
  "type": "request",
  "message": "delete",
  "resource": "/connection",
}
```
Message accepted response
```json
{
  "type": "response",
  "message": "delete",
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
  "message": "delete",
  "resource": "/connection",
  "notification": {
    "code": 204,
  }
}
```
