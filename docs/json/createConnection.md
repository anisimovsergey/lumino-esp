## Create connection
Request
```json
{
  "_type": "request",
  "requestType": "create",
  "resource": "connection",
  "content" : {
    "type": "connection",
    "wifi_network": "network SSID",
    "wifi_password": "password"
  }
}
```
Response
```json
{
  "_type": "response",
  "requestType": "create",
  "resource": "connection",
  "result": {
    "type": "statusResult",
    "code": 201,
    "text": "Created"
  }
}
```
Event
```json
{
  "_type": "event",
  "eventType": "deleted",
  "resource": "connection",
  "result": {
    "type": "connection",
    "network": "network name",
    "isConnected": true
  }
}
```
