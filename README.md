
# Auction Engine
This implements an auction and bid tracking system. An overview and description of the of the functionality is given here. The full Doxygen API can be viewed [here](http://eg.bucknell.edu/~rae018/auction_engine/docs/annotated.html). 

There are three main classes and a struct:
- Auction
- User
- Item
- Bid (struct)

Users and Items are created using Auction::addUser() and Auction::addItem() methods, each which take a name for the user or item (in addition to optional initial funds and starting value) to which the auction assigns an ID too. IDs and name for items and users must be unique only for each type, e.g. there can be an item and user both with ID 16 but not two users or two items. An auction instance is the sole owner of all user and item objects registered with it, and they are stored in a map indexed by ID. All lists of users or items in other objects is done by ID alone, and access to the actual user or item object can be obtained with the Auction::getUser() and Auction::getItem() methods which take an ID and a constant reference to a pointer which is assigned to the corresponding user or item object. 

The User and Item class contain information relating to users and items with some convenient methods for accessing and manipulating this information. See the full docs for details. The Bid struct contains information related to a specific bid such as the user that placed it, the item it was placed on, and its value. Its comparison operators are overloaded to compare value members.

#### Auction Class and Making Bids
The Auction class serves as the driving class. All error checking is done  here. For instance, User::addBid() does not check that bids value is less than or equal to the user's funds and is not meant to be called alone - this must be done before it is called which the Auction class does. This class contains all methods need for placing and tracking bids. Once an item is registered in the auction, it must be opened for bidding with Auction::openItem() before bids can be placed on it. Once open, registered users can place bids on it with Auction::placeBid() which takes an item ID of the item to bid in, a user ID of the user placing the bid, and a bid value. A bid is valid if:
- the item is registered, open, and has not been sold
- the user is registered
- the bid value is not greater than the user's available funds plus their current bid on the item. 
- the bid value is greater than the current high bid value, or if there are not current bids then greater than or equal to the item's starting value

A return status containing and error code and message is returned if any of these conditions is not met. Otherwise it return an OK status. 

A users available funds are calculated as their total funds minus their highest outstanding bids on any items. For example, if a user has bid twice on an item, only the higher bid value would be subtracted to get the available funds. When an item gets sold, if the user has lost, their highest bid on it gets added back to their available funds. If they win, their high bid gets subtracted from their total funds and the available funds stay the same. When determining if a bid is valid, the users highest bid on the item is added to the available funds which represent how much they can "up" their bid. For example if a users current bid on an item is 50 and they have 20 available funds, they can bid up to 70 on this item, but no more than 20 on a new item. 

For the full API and feature list, see the Doxygen pages linked above and view the test/demo files for example uses.




