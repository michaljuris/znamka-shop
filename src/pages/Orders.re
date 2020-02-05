module GetOrders = [%graphql
  {|
    query getOrders {
      orders(limit: 30) {
        id
        email
        license_plate
        validFrom
        tariff {
         id
         currency
         tariffDuration
         price
        }
      }
    }
  |}
];

module GetOrdersQuery = ReasonApolloHooks.Query.Make(GetOrders);

[@react.component]
let make = () => {
  let (orders, _resultObject) =
    GetOrdersQuery.use(
      ~fetchPolicy=ReasonApolloHooks.Types.CacheAndNetwork,
      (),
    );

  <>
    <PageHeading text="Znamka orders" />
    {switch (orders) {
     | NoData => <div> {React.string("No orders yet")} </div>
     | Error(_error) =>
       <div> {React.string("Error while loading orders")} </div>
     | Loading => <div> {React.string("Loading orders")} </div>
     | Data(response) => <OrderList orders=response />
     }}
  </>;
};
