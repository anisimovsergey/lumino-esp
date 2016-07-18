## Create connection
Request
```json
{
  "type": "request",
  "action": "create",
  "resource": "/connection",
  "content" : {
    "type": "connection",
    "wifi_network": "network SSID",
    "wifi_password": "password"
  }
}
```
Message accepted response
```json
{
  "type": "response",
  "action": "create",
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
  "action": "create",
  "resource": "/connection",
  "result": {
    "type": "statusResult",
    "code": 302,
    "attributes" : {
      "location": "/connection"
    }
  }
}
```
