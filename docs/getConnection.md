## Get connection
Request
```json
{
  "type": "request",
  "action": "get",
  "resource": "/connection"
}
```
Message accepted response
```json
{
  "type": "response",
  "action": "get",
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
