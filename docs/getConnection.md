## Get connection
Request
```json
{
  "type": "request",
  "action": "get",
  "resource": "/connection"
}
```
Response (successful)
```json
{
  "type": "response",
  "action": "get",
  "resource": "/connection",
  "result": {
    "type": "objectResult",
    "object" : {
      "type": "connection",
      "network": "network name",
      "isConnected": true
    }
  }
}
```
Response (error)
```json
{
  "type": "response",
  "action": "get",
  "resource": "/connection",
  "result": {
    "type": "statusResult",
    "code": 404,
    "text": "NotFound"
  }
}
```
