## Get connection
Request
```json
{
  "_type": "request",
  "requestType": "read",
  "resource": "connection"
}
```
Response (successful)
```json
{
  "_type": "response",
  "requestType": "read",
  "resource": "connection",
  "result": {
    "type": "connection",
    "network": "network name",
    "isConnected": true
  }
}
```
Response (error)
```json
{
  "_type": "response",
  "requestType": "read",
  "resource": "connection",
  "result": {
    "type": "status",
    "code": 404,
    "text": "NotFound"
  }
}
```
