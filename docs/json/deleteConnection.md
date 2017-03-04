## Delete connection
Request
```json
{
  "_type": "request",
  "requestType": "delete",
  "resource": "connection"
}
```
Response
```json
{
  "_type": "response",
  "requestType": "delete",
  "resource": "connection",
  "result": {
    "type": "status",
    "code": 204,
    "text": "The connection was deleted."
  }
}
```
Event
```json
{
  "_type": "event",
  "eventType": "deleted",
  "resource": "connection"
}
```
