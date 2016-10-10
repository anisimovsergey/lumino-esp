## Delete connection
Request
```json
{
  "type": "request",
  "action": "delete",
  "resource": "connection"
}
```
Response
```json
{
  "type": "response",
  "action": "delete",
  "resource": "connection",
  "result": {
    "type": "statusResult",
    "code": 204,
    "text": "NoContent"
  }
}
```
Notification
```json
{
  "type": "notification",
  "action": "delete",
  "resource": "connection",
  "result": {
    "type": "statusResult",
    "code": 204,
    "text": "NoContent"
  }
}
```
