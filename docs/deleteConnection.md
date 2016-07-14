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
  "message": "delete",
  "resource": "/connection",
  "result": {
    "type": "statusResult",
    "code": 204,
  }
}
```
