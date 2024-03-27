This program is a SMTP_Client example running on Network Dual Stack.
It shows you how to send emails from an embedded application.

To test this example, connect the evaluation board to a LAN with router.
The example will configure the network parameters automatically.

Note:
In order to make the example work, you need to modify SMTP_Client.c:
- Modify Email information content in the SMTP Email Descriptor structure (NET_SMTP_MAIL mail):
  - Email addresses: From, To, Cc, Bcc
  - Subject and the message (body) of the Email
  - Optional attachments and encoding type

- Modify information about SMTP Server and user credentials in SMTP
  Mail Transfer Agent Descriptor structure (NET_SMTP_MTA server):
  - Server name/IP
  - Sever port
  - User name and password
  - Optional NET_SMTP_MTA_USETLS flag in case of secure variant.
    (https://www.keil.com/pack/doc/mw/Network/html/use_secure_components.html#smtps_client)
