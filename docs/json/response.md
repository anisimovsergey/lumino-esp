
In case of an unrecognized request the response contains the following
```json
{
  "_type": "response",
  "result": {
    "type": "status",
    "code": 400
  }
}
```
Please note that fields `message` and `resource` are missing in this case.

In case of a recognized but not processed request the response contains the following
```json
{
  "_type": "response",
  "requestType": "read",
  "resource": "someUnknownResource",
  "result": {
    "type": "status",
    "code": 404,
    "message": "ResourceNotFound"
  }  
}
```
