## Create connection
Request
```json
{
  "type": "request",
  "action": "create",
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
  "type": "response",
  "action": "create",
  "resource": "connection",
  "result": {
    "type": "statusResult",
    "code": 201,
    "text": "Created"
  }
}
```
Notification
```json
{
  "type": "notification",
  "action": "create",
  "resource": "connection",
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
