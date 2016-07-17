In case of an unrecognized request the response contains the following
```json
{
  "type": "response",
  "result": {
    "type": "statusResult",
    "code": 400
  }
}
```
Please note that fields `message` and `resource` are missing in this case.

In case of a recognized but not processed request the response contains the following
```json
{
  "type": "response",
  "message": "get",
  "resource": "/unknownResource",
  "result": {
    "type": "statusResult",
    "code": 404,
    "message": "ResourceNotFound"
  }  
}
```
