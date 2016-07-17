## Delete connection
Request
```json
{
  "type": "request",
  "action": "delete",
  "resource": "/connection",
}
```
Message accepted response
```json
{
  "type": "response",
  "action": "delete",
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
  "action": "delete",
  "resource": "/connection",
  "result": {
    "type": "statusResult",
    "code": 204,
  }
}
```
